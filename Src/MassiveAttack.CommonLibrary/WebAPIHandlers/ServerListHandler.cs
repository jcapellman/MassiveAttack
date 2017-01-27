using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.GameServers;

using System.Collections.Generic;
using System.Threading.Tasks;

namespace MassiveAttack.Common.Library.WebAPIHandlers
{
    public class ServerListHandler : BaseWebAPIHandler
    {
        public ServerListHandler(HandlerConstructorItem constructorItem) : base(constructorItem)
        {
        }

        public async Task<List<GameServerListResponseItem>> GetServerListAsync() => await GetAsync<List<GameServerListResponseItem>>("Server");
    }
}