using MassiveAttack.Common.Library.Objects.WebAPI.Internal;

namespace MassiveAttack.WebAPI.BusinessLibrary.Managers {
    public class BaseManager {
        private readonly ControllerHandlerItem _controllerHandlerItem;

        protected string SQLServerConnectionString => _controllerHandlerItem.SQLServerConnectionString;

        protected string RedisConnectionString => _controllerHandlerItem.RedisConnectionString;
        
        public BaseManager(ControllerHandlerItem controllerHandlerItem) {
            _controllerHandlerItem = controllerHandlerItem;
        }
    }
}