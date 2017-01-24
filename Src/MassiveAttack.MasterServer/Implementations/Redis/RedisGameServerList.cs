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

        private void InitRedis()
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
            InitRedis();

            // TODO: Implement List functionality
            return new List<GameServerListResponseItem>();
        }

        public async Task<string> UpdateListAsync(GameServerPingBackRequestItem requestItem)
        {
            InitRedis();    

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