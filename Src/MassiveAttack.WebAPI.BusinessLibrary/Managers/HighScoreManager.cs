using System;
using System.Collections.Generic;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.HighScore;
using MassiveAttack.Common.Library.Objects.WebAPI.Internal;

using MassiveAttack.WebAPI.DataLibrary.EFModel;
using MassiveAttack.WebAPI.DataLibrary.Objects.HighScores;
using MassiveAttack.WebAPI.DataLibrary.RModel;

namespace MassiveAttack.WebAPI.BusinessLibrary.Managers {
    public class HighScoreManager : BaseManager {
        public HighScoreManager(ControllerHandlerItem controllerHandlerItem) : base(controllerHandlerItem) { }

        private async void updateHighScore(Guid levelGUID) {
            using (var hsModel = new HighScoreModel(SQLServerConnectionString)) {
                using (var rModel = new RedisModel(RedisConnectionString)) {
                    // TODO Pull in top 10 scores for a given level, create list collection, write to Redis
                }
            }
        }

        public async Task<ReturnSet<bool>> AddHighScore(HighScoreRequestItem requestItem) {
            using (var hsModel = new HighScoreModel(SQLServerConnectionString)) {
                var newHighScore = new HighScores {
                    LevelGUID = requestItem.LevelGUID,
                    PlayerGUID = requestItem.PlayerGUID,
                    Score = requestItem.Score
                };

                hsModel.HighScore.Add(newHighScore);
                var response = await hsModel.SaveChangesAsync();

                updateHighScore(requestItem.LevelGUID);

                return new ReturnSet<bool>(response > 0);
            }
        }

        public async Task<ReturnSet<List<HighScoreListingResponseItem>>> GetHighScores(Guid LevelGUID) {
            var result = await GetRedisObject<List<HighScoreListingResponseItem>>(LevelGUID);
            
            return result.HasError ? new ReturnSet<List<HighScoreListingResponseItem>>(result.ExceptionThrown) : new ReturnSet<List<HighScoreListingResponseItem>>(result.ObjectValue);
        }

        public override string GetRedisPrefix() => "HighScores";
    }
}