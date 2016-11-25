using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;

using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.HighScore;

using MassiveAttack.WebAPI.BusinessLibrary.Managers;

namespace MassiveAttack.WebAPI.Controllers {
    public class HighScoreController : BaseController {
        [HttpGet]
        public async Task<ReturnSet<List<HighScoreListingResponseItem>>> GET(Guid levelGUID)
            => await new HighScoreManager(ControllerHandlerItem).GetHighScores(levelGUID);

        [HttpPut]
        public async Task<ReturnSet<bool>> PUT(HighScoreRequestItem requestItem) =>
            await new HighScoreManager(ControllerHandlerItem).AddHighScore(requestItem);
    }
}