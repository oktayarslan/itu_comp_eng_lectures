﻿//------------------------------------------------------------------------------
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
    using System.Data.Entity;
    using System.Data.Entity.Infrastructure;
    
    public partial class Entities : DbContext
    {
        public Entities()
            : base("name=Entities")
        {
        }
    
        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            throw new UnintentionalCodeFirstException();
        }
    
        public DbSet<Answer> Answer { get; set; }
        public DbSet<Badge> Badge { get; set; }
        public DbSet<Comment> Comment { get; set; }
        public DbSet<Question> Question { get; set; }
        public DbSet<QuestionTag> QuestionTag { get; set; }
        public DbSet<Reputation> Reputation { get; set; }
        public DbSet<Tag> Tag { get; set; }
        public DbSet<User> User { get; set; }
        public DbSet<UserBadge> UserBadge { get; set; }
        public DbSet<UserTag> UserTag { get; set; }
    }
}