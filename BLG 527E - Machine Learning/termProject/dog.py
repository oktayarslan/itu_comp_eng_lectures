import numpy
import cv2
import imutils
import pandas
from tqdm import tqdm
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

import keras
from keras.models import Model
from keras.layers import Dense, Dropout, Flatten


from keras.layers import Conv2D, MaxPooling2D, GlobalAveragePooling2D
from keras.layers import Dropout, Flatten, Dense
from keras.models import Sequential


# initialize the list of class labels MobileNet SSD was trained to
# detect, then generate a set of bounding box colors for each class
CLASSES = ["background", "aeroplane", "bicycle", "bird", "boat",
           "bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
           "dog", "horse", "motorbike", "person", "pottedplant", "sheep",
           "sofa", "train", "tvmonitor"]

# load our serialized model from disk
net = cv2.dnn.readNetFromCaffe("MobileNetSSD_deploy.prototxt.txt", "MobileNetSSD_deploy.caffemodel")

df_train = pandas.read_csv('labels.csv')
df_test = pandas.read_csv('sample_submission.csv')

targets_series = pandas.Series(df_train['breed'])
one_hot = pandas.get_dummies(targets_series, sparse = True)
one_hot_labels = numpy.asarray(one_hot)

img_size = 150


x_train = []
y_train = []
x_test = []


for i, sample in enumerate(df_train['id']):
    image = cv2.imread('train/' + sample + '.jpg')
    (h, w) = image.shape[:2]
    blob = cv2.dnn.blobFromImage(cv2.resize(image, (300, 300)), 0.007843, (300, 300), 127.5)

    # pass the blob through the network and obtain the detections and
    # predictions
    net.setInput(blob)
    detections = net.forward()

    # detect dog with highest confidence
    dogmatch = filter(lambda x: x[1] == 12, detections[0][0])
    # if dog is not detected try similar classes
    if len(dogmatch) == 0:
        dogmatch = filter(lambda x: x[1] in (8, 3, 17, 13, 10), detections[0][0])

    if len(dogmatch) > 0:
        box = dogmatch[0][3:7] * numpy.array([w, h, w, h])
        (startX, startY, endX, endY) = box.astype("int").clip(min=0)
        image = image[startY:endY, startX:endX]

    x_train.append(cv2.resize(image, (img_size, img_size)))
    y_train.append(one_hot_labels[i])


for i, sample in enumerate(df_test['id']):
    image = cv2.imread('test/' + sample + '.jpg')
    (h, w) = image.shape[:2]
    blob = cv2.dnn.blobFromImage(cv2.resize(image, (300, 300)), 0.007843, (300, 300), 127.5)

    # pass the blob through the network and obtain the detections and
    # predictions
    net.setInput(blob)
    detections = net.forward()

    # detect dog with highest confidence
    dogmatch = filter(lambda x: x[1] == 12, detections[0][0])
    # if dog is not detected try similar classes
    if len(dogmatch) == 0:
        dogmatch = filter(lambda x: x[1] in (8, 3, 17, 13, 10), detections[0][0])

    if len(dogmatch) > 0:
        box = dogmatch[0][3:7] * numpy.array([w, h, w, h])
        (startX, startY, endX, endY) = box.astype("int").clip(min=0)
        image = image[startY:endY, startX:endX]

    x_test.append(cv2.resize(image, (img_size, img_size)))


y_train_raw = numpy.array(y_train, numpy.uint8)
x_train_raw = numpy.array(x_train, numpy.float32) / 255.
x_test  = numpy.array(x_test, numpy.float32) / 255.

X_train, X_test, y_train, y_test = train_test_split(x_train_raw, y_train_raw, test_size=0.3, random_state=1)

model = Sequential()
model.add(Conv2D(filters=16, kernel_size=2, padding='same', activation='relu', 
                        input_shape=(img_size, img_size, 3)))
model.add(MaxPooling2D(pool_size=2))
model.add(Conv2D(filters=32, kernel_size=2, padding='same', activation='relu'))
model.add(MaxPooling2D(pool_size=2))
model.add(Conv2D(filters=64, kernel_size=2, padding='same', activation='relu'))
model.add(MaxPooling2D(pool_size=2))
model.add(Dropout(0.3))
model.add(Flatten())
model.add(Dense(500, activation='relu'))
model.add(Dropout(0.4))
model.add(Dense(120, activation='softmax'))

model.compile(optimizer='rmsprop', loss='categorical_crossentropy', metrics=['accuracy'])


model.summary()


model.fit(X_train, y_train, epochs=1, validation_data=(X_test, y_test), verbose=1)

preds = model.predict(x_test, verbose=1)

sub = pandas.DataFrame(preds)
# Set column names to those generated by the one-hot encoding earlier
col_names = one_hot.columns.values
sub.columns = col_names
# Insert the column id from the sample_submission at the start of the data frame
sub.insert(0, 'id', df_test['id'])
sub.to_csv('out.csv', index=False)
