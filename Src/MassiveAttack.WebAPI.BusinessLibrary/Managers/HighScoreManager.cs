using System;
using System.Collections.Generic;
using System.Linq;

using MassiveAttack.CommonLibrary.Objects.Common;
using MassiveAttack.CommonLibrary.Objects.WebAPI.HighScore;
using MassiveAttack.CommonLibrary.Objects.WebAPI.Internal;

using MassiveAttack.WebAPI.DataLibrary.EFModel;

namespace MassiveAttack.WebAPI.BusinessLibrary.Managers {
    public class HighScoreManager : BaseManager {
        public HighScoreManager(ControllerHandlerItem controllerHandlerItem) : base(controllerHandlerItem) { }

        public ReturnSet<List<HighScoreListingResponseItem>> GetHighScores(Guid LevelGUID) {
            using (var hsModel = new HighScoreModel(ConnectionString)) {
                return
                    new ReturnSet<List<HighScoreListingResponseItem>>(hsModel.HighScore.Where(a => a.LevelGUID == LevelGUID)
                        .ToList()
                        .Select(b => new HighScoreListingResponseItem { PlayerName = "Test", Score = b.Score })
                        .ToList());
            }
        }
    }
}