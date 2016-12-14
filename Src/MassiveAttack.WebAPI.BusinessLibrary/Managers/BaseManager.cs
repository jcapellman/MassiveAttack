using System;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.Internal;

using MassiveAttack.WebAPI.DataLibrary.RModel;

namespace MassiveAttack.WebAPI.BusinessLibrary.Managers {
    public abstract class BaseManager {
        private readonly ControllerHandlerItem _controllerHandlerItem;

        public Guid CurrentPlayerGUID => _controllerHandlerItem.PlayerGUID;

        public abstract string GetRedisPrefix();

        public string GetRedisKey(Guid objectGuid) => $"{GetRedisPrefix()}_{objectGuid}";

        protected string SQLServerConnectionString => _controllerHandlerItem.SQLServerConnectionString;

        protected string RedisConnectionString => _controllerHandlerItem.RedisConnectionString;

        protected async Task<ReturnSet<T>> GetRedisObject<T>(Guid objectGUID) {
            using (var rModel = new RedisModel(RedisConnectionString)) {
                return await rModel.Get<T>(GetRedisKey(objectGUID));
            }
        }

        protected async Task<ReturnSet<bool>> WriteRedisObject<T>(Guid objectGUID, T objectValue) {
            using (var rModel = new RedisModel(RedisConnectionString)) {
                return await rModel.Write(GetRedisKey(objectGUID), objectValue);
            }
        }

        protected async Task<bool> DeleteRedisObject(Guid objectGUID) {
            using (var rModel = new RedisModel(RedisConnectionString)) {
                return await rModel.Delete(GetRedisKey(objectGUID));
            }
        }

        protected BaseManager(ControllerHandlerItem controllerHandlerItem) {
            _controllerHandlerItem = controllerHandlerItem;
        }
    }
}