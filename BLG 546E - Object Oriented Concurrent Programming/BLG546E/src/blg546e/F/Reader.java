/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e.F;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author ovatman
 */
public class Reader implements Runnable{
    private ReadWriteClass rwo;

    public Reader(ReadWriteClass rwo) {
        this.rwo = rwo;
    }
    
    
    @Override
    public void run() {
        
       
        int val = rwo.getValue();
        
    }
    
}