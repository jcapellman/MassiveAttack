using System;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.Common;

using Newtonsoft.Json;

using StackExchange.Redis;

namespace MassiveAttack.WebAPI.DataLibrary.RModel {
    public class RedisModel : IDisposable {
        private static ConnectionMultiplexer _redis;
        private IDatabase _db;

        private readonly string _connectionString;

        public RedisModel(string connectionString) {
            _connectionString = connectionString;
        }

        private string convertToJson<T>(T objectValue) => JsonConvert.SerializeObject(objectValue);

        private T convertJsonToT<T>(string strValue) => (T)JsonConvert.DeserializeObject(strValue);

        private void connect() {
            if (_redis == null) {
                _redis = ConnectionMultiplexer.Connect(_connectionString);
            }

            if (_db == null) {
                _db = _redis.GetDatabase();
            }
        }

        public async Task<ReturnSet<T>> Get<T>(string key) {
            try {
                connect();

                var json = await _db.StringGetAsync(key);

                if (!json.HasValue) {
                    throw new Exception($"Could not load key ({key})");
                }

                return new ReturnSet<T>(convertJsonToT<T>(json.ToString()));
            } catch (Exception ex) {
                return new ReturnSet<T>(ex);
            }
        }

        public async Task<ReturnSet<bool>> Write<T>(string key, T objectValue) {
            try {
                connect();

                await _db.StringSetAsync(key, convertToJson(objectValue), flags: CommandFlags.FireAndForget);

                return new ReturnSet<bool>(true);
            } catch (Exception ex) {
                return new ReturnSet<bool>(ex);
            }
        }

        public async void Delete(string key) {
            connect();

            await _db.KeyDeleteAsync(key, CommandFlags.FireAndForget);
        }

        public void Dispose() {
            _redis.Close(true);
        }
    }
}