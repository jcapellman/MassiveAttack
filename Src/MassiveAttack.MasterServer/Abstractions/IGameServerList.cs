using System;
using System.Collections.Generic;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.WebAPI.GameServers;

namespace MassiveAttack.MasterServer.Abstractions
{
    public interface IGameServerList
    {
        List<GameServerListResponseItem> GetActiveList();

        Task<string> UpdateList(GameServerPingBackRequestItem requestItem);
    }
}