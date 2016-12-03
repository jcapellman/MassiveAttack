using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.GameMetrics;
using MassiveAttack.Common.Library.Objects.WebAPI.Internal;

using MassiveAttack.WebAPI.DataLibrary.EFModel;
using MassiveAttack.WebAPI.DataLibrary.Objects.GameMetrics;

namespace MassiveAttack.WebAPI.BusinessLibrary.Managers {
    public class GameMetricManager : BaseManager {
        public GameMetricManager(ControllerHandlerItem controllerHandlerItem) : base(controllerHandlerItem) { }

        public override string GetRedisPrefix() => "GAMEMETRIC";

        public async Task<ReturnSet<bool>> AddGameMetric(GameMetricRequestItem requestItem) {
            try {
                using (var gModel = new GameMetricModel(SQLServerConnectionString)) {
                    var metric = new GameMetrics {
                        LevelGUID = requestItem.LevelGUID,
                        PlayerGUID = CurrentPlayerGUID,
                        BulletsFired = requestItem.BulletsFired,
                        DamageInflicted = requestItem.DamageInflicted,
                        DurationInSeconds = requestItem.DurationInSeconds,
                        Victorious = requestItem.Victorious
                    };

                    gModel.GameMetrics.Add(metric);

                    await gModel.SaveChangesAsync();

                    return new ReturnSet<bool>(true);
                }
            } catch (Exception ex) {
                return new ReturnSet<bool>(ex);
            }
        }

        public async Task<ReturnSet<List<GameMetricListingResponseItem>>> GetMetricsForPlayer(Guid playerGUID) {
            try {
                using (var gModel = new GameMetricModel(SQLServerConnectionString)) {
                    var rMetrics = await GetRedisObject<List<GameMetricListingResponseItem>>(playerGUID);

                    if (!rMetrics.HasError) {
                        return new ReturnSet<List<GameMetricListingResponseItem>>(rMetrics.ObjectValue);
                    }

                    var metrics = gModel.GameMetrics.Where(a => a.PlayerGUID == playerGUID).ToList().Select(b => new GameMetricListingResponseItem {
                        BulletsFired = b.BulletsFired,
                        DamageInflicted = b.DamageInflicted,
                        Victorious = b.Victorious,
                        DurationInSeconds = b.DurationInSeconds,
                        DatePlayed = b.CreatedDate.DateTime,
                        LevelName = "test"
                    }).ToList();

                    await WriteRedisObject(playerGUID, metrics);

                    return new ReturnSet<List<GameMetricListingResponseItem>>(metrics);
                }
            } catch (Exception ex) {
                return new ReturnSet<List<GameMetricListingResponseItem>>(ex);
            }
        }
    }
}