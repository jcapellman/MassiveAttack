using System;
using System.Collections.Generic;
using System.Threading.Tasks;

using Microsoft.AspNetCore.Mvc;

using MassiveAttack.Common.Library.Objects.WebAPI.GameMetrics;
using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.WebAPI.BusinessLibrary.Managers;

namespace MassiveAttack.WebAPI.Controllers {
    public class GameMetricsController : BaseController {
        [HttpGet]
        public async Task<ReturnSet<List<GameMetricListingResponseItem>>> GET(Guid playerGUID)
            => await new GameMetricManager(ControllerHandlerItem).GetMetricsForPlayer(playerGUID);

        [HttpPut]
        public async Task<ReturnSet<bool>> PUT(GameMetricRequestItem requestItem)
            => await new GameMetricManager(ControllerHandlerItem).AddGameMetric(requestItem);
    }
}