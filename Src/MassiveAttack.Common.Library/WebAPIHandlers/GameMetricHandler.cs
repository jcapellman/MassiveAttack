using System;
using System.Collections.Generic;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.GameMetrics;

namespace MassiveAttack.Common.Library.WebAPIHandlers {
    public class GameMetricHandler : BaseWebAPIHandler {
        public GameMetricHandler(HandlerConstructorItem constructorItem) : base(constructorItem) { }

        public async Task<ReturnSet<bool>> AddGameMetric(GameMetricRequestItem requestItem)
            => await PutAsync<GameMetricRequestItem, ReturnSet<bool>>("GameMetrics", requestItem);

        public async Task<ReturnSet<List<GameMetricListingResponseItem>>> GetGameMetrics(Guid playerGUID)
            => await GetAsync<ReturnSet<List<GameMetricListingResponseItem>>>($"GameMetrics?playerGUID={playerGUID}");
    }
}