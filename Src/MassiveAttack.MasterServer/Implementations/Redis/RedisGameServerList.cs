using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

using MassiveAttack.MasterServer.Abstractions;
using MassiveAttack.Common.Library.Objects.WebAPI.GameServers;
using MassiveAttack.MasterServer.Implementations.Redis.Objects;

using StackExchange.Redis;
using Newtonsoft.Json;
using System.Text;

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

        public async Task<List<GameServerListResponseItem>> GetActiveListAsync()
        {
            InitRedis();

            var serverList = await db.ListRangeAsync("Servers");

            return serverList.Select(a => JsonConvert.DeserializeObject<GameServerItem>(a)).Select(b => new GameServerListResponseItem {
                CurrentMap = b.CurrentMap,
                MaxPlayers = b.MaxPlayers,
                NumPlayers = b.NumPlayers,
                ServerID = b.ServerID,
                ServerTitle = b.ServerTitle
            }).ToList();            
        }

        private string generateHash(string stringToHash)
        {
            var bytes = System.Security.Cryptography.SHA256.Create().ComputeHash(Encoding.ASCII.GetBytes(stringToHash));

            var hash = string.Empty;

            foreach (var shaByte in bytes)
            {
                hash += shaByte.ToString("x2");
            }
            
            return hash;
        }

        public async Task<string> UpdateListAsync(GameServerPingBackRequestItem requestItem)
        {
            InitRedis();
            
            if (string.IsNullOrEmpty(requestItem.ServerID))
            {
                requestItem.ServerID = generateHash(JsonConvert.SerializeObject(requestItem));
            }

            var gameServerItem = new GameServerItem
            {
                CurrentMap = requestItem.CurrentMap,
                LastPingBack = DateTimeOffset.Now,
                MaxPlayers = requestItem.MaxPlayers,
                NumPlayers = requestItem.NumPlayers,
                ServerTitle = requestItem.ServerTitle,
                ServerID = requestItem.ServerID
            };
            
            await db.ListRightPushAsync("Servers", JsonConvert.SerializeObject(gameServerItem), flags: CommandFlags.FireAndForget);
            
            return requestItem.ServerID;
        }
    }
}