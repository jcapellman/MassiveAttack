using System.Collections.Generic;

using Microsoft.AspNetCore.Mvc;

namespace MassiveAttack.WebAPI.Controllers {
    public class HighScoreController : BaseController {
        [HttpGet]
        public IEnumerable<string> Get() {
            return new string[] { "value1", "value2" };
        }
        
        [HttpGet("{id}")]
        public string Get(int id) {
            return "value";
        }
    }
}