//------------------------------------------------------------------------------
// <auto-generated>
//    This code was generated from a template.
//
//    Manual changes to this file may cause unexpected behavior in your application.
//    Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace Model
{
    using System;
    using System.Collections.Generic;
    
    public partial class Question
    {
        public System.Guid ID { get; set; }
        public System.Guid UserID { get; set; }
        public string Title { get; set; }
        public string Text { get; set; }
        public System.DateTime CreateDate { get; set; }
        public bool IsDeleted { get; set; }
    
        public virtual User User { get; set; }
    }
}