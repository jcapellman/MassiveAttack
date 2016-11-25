using MassiveAttack.CommonLibrary.Objects.WebAPI.Internal;

namespace MassiveAttack.WebAPI.BusinessLibrary.Managers {
    public class BaseManager {
        private readonly ControllerHandlerItem _controllerHandlerItem;

        protected string ConnectionString => _controllerHandlerItem.ConnectionString;

        public BaseManager(ControllerHandlerItem controllerHandlerItem) {
            _controllerHandlerItem = controllerHandlerItem;
        }
    }
}