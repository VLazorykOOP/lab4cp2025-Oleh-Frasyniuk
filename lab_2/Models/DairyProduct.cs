using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_4.Models
{
    public class DairyProduct
    {
        public int Id { get; set; }
        public string Name { get; set; }         
        public string Category { get; set; }     
        public string Type { get; set; }         
        public DateTime ExpirationDate { get; set; } 
        public string Supplier { get; set; }    
        public decimal Price { get; set; }       
    }
}
