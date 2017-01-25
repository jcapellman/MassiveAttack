using System.Collections.Generic;
using System.Threading.Tasks;

using Microsoft.AspNetCore.Mvc;

using MassiveAttack.Common.Library.Objects.WebAPI.GameServers;
using MassiveAttack.MasterServer.Abstractions;

namespace MassiveAttack.MasterServer.Controllers
{   
    public class ServerController : BaseController
    {
        private IGameServerList _gameServerList;

        public ServerController(IGameServerList gameServerList) {
            _gameServerList = gameServerList;
        }

        [HttpGet]
        public async Task<List<GameServerListResponseItem>> GetServerListAsync() => await _gameServerList.GetActiveListAsync();

        [HttpPost]
        public async Task<string> AddPingBackAsync(GameServerPingBackRequestItem requestItem) => await _gameServerList.UpdateListAsync(requestItem);
    }
}