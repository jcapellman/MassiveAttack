using System.Collections.Generic;

using Microsoft.AspNetCore.Mvc;

using MassiveAttack.Common.Library.Objects.WebAPI.GameServers;
using MassiveAttack.MasterServer.Abstractions;
using System.Threading.Tasks;

namespace MassiveAttack.MasterServer.Controllers
{   
    public class ServerController : BaseController
    {
        private IGameServerList _gameServerList;

        public ServerController(IGameServerList gameServerList) {
            _gameServerList = gameServerList;
        }

        [HttpGet]
        public List<GameServerListResponseItem> GET() => _gameServerList.GetActiveList();

        [HttpPost]
        public async Task<string> POST(GameServerPingBackRequestItem requestItem) => await _gameServerList.UpdateList(requestItem);
    }
}