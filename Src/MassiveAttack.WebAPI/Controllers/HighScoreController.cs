using System;
using System.Collections.Generic;

using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.HighScore;

using Microsoft.AspNetCore.Mvc;
using MassiveAttack.WebAPI.BusinessLibrary.Managers;

namespace MassiveAttack.WebAPI.Controllers {
    public class HighScoreController : BaseController {
        [HttpGet]
        public ReturnSet<List<HighScoreListingResponseItem>> GET(Guid levelGUID)
            => new HighScoreManager(ControllerHandlerItem).GetHighScores(levelGUID);
    }
}