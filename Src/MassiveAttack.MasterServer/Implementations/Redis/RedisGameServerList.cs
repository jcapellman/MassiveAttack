using System;
using System.Collections.Generic;
using System.Threading.Tasks;

using MassiveAttack.MasterServer.Abstractions;
using MassiveAttack.Common.Library.Objects.WebAPI.GameServers;
using MassiveAttack.MasterServer.Implementations.Redis.Objects;

using StackExchange.Redis;
using Newtonsoft.Json;

namespace MassiveAttack.MasterServer.Implementations.Redis
{
    public class RedisGameServerList : IGameServerList
    {
        private static ConnectionMultiplexer redis;
        private IDatabase db;

        private void initRedis()
        {
            if (redis == null)
            {
                redis = ConnectionMultiplexer.Connect("localhost");
            }

            if (db == null)
            {
                db = redis.GetDatabase();
            }
        }

        public List<GameServerListResponseItem> GetActiveList()
        {
            initRedis();

            // TODO: Implement List functionality
            return new List<GameServerListResponseItem>();
        }

        public async Task<string> UpdateList(GameServerPingBackRequestItem requestItem)
        {
            initRedis();    

            var gameServerItem = new GameServerItem
            {
                CurrentMap = requestItem.CurrentMap,
                LastPingBack = DateTimeOffset.Now,
                MaxPlayers = requestItem.MaxPlayers,
                NumPlayers = requestItem.NumPlayers,
                ServerTitle = requestItem.ServerTitle
            };

            // TODO: Handle Scenario on first ping back
            await db.StringSetAsync(requestItem.ServerID, JsonConvert.SerializeObject(gameServerItem), flags: CommandFlags.FireAndForget);

            return requestItem.ServerID;
        }
    }
}