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

        public async Task<ReturnSet<bool>> AddHighScore(HighScoreRequestItem requestItem) {
            using (var hsModel = new HighScoreModel(SQLServerConnectionString)) {
                var newHighScore = new HighScores {
                    LevelGUID = requestItem.LevelGUID,
                    PlayerGUID = requestItem.PlayerGUID,
                    Score = requestItem.Score
                };
                
                hsModel.HighScore.Add(newHighScore);
                var response = await hsModel.SaveChangesAsync();

                return new ReturnSet<bool>(response > 0);
            }
        }

        public async Task<ReturnSet<List<HighScoreListingResponseItem>>> GetHighScores(Guid LevelGUID) {
            using (var rModel = new RedisModel(RedisConnectionString)) {
                var result = await rModel.Get<List<HighScoreListingResponseItem>>($"HighScores_{LevelGUID}");

                return result.HasError ? new ReturnSet<List<HighScoreListingResponseItem>>(result.ExceptionThrown) : new ReturnSet<List<HighScoreListingResponseItem>>(result.ObjectValue);
            }
        }
    }
}