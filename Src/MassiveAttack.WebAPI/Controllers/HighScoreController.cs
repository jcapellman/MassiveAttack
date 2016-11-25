using System;
using System.Collections.Generic;

using MassiveAttack.CommonLibrary.Objects.Common;
using MassiveAttack.CommonLibrary.Objects.WebAPI.HighScore;

using MassiveAttack.WebAPI.BusinessLayer.Managers;

using Microsoft.AspNetCore.Mvc;

namespace MassiveAttack.WebAPI.Controllers {
    public class HighScoreController : BaseController {
        [HttpGet]
        public ReturnSet<List<HighScoreListingResponseItem>> GET(Guid levelGUID)
            => new HighScoreManager(ControllerHandlerItem).GetScores(levelGUID);
    }
}