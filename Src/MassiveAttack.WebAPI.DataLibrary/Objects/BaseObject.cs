using System;
using System.ComponentModel.DataAnnotations;

namespace MassiveAttack.WebAPI.DataLibrary.Objects {
    public class BaseObject {
        [Key]
        public int ID { get; set; }

        [Required]
        public DateTimeOffset ModifiedDate { get; set; }

        [Required]
        public DateTimeOffset CreatedDate { get; set; }

        [Required]
        public int StatusID { get; set; }
    }
}