using System;
using System.Collections.Generic;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.HighScore;

namespace MassiveAttack.Common.Library.WebAPIHandlers {
    public class HighScoreHandler : BaseWebAPIHandler {
        public HighScoreHandler(string webapiAddress, string token = null) : base(webapiAddress, token) { }

        public async Task<ReturnSet<List<HighScoreListingResponseItem>>> GetHighScores(Guid levelGUID) =>
            await GetAsync<ReturnSet<List<HighScoreListingResponseItem>>>($"HighScore?levelGUID={levelGUID}");
    }
}