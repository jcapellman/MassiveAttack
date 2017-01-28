using System.Collections.Generic;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.WebAPI.GameServers;

namespace MassiveAttack.MasterServer.WebAPI.Abstractions
{
    public interface IGameServerList
    {
        Task<List<GameServerListResponseItem>> GetActiveListAsync();

        Task<string> UpdateListAsync(GameServerPingBackRequestItem requestItem);
    }
}