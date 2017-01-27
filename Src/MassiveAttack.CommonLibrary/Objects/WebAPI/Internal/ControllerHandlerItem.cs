using System;

namespace MassiveAttack.Common.Library.Objects.WebAPI.Internal {
    public class ControllerHandlerItem {
        public string SQLServerConnectionString { get; set; }

        public string RedisConnectionString { get; set; }

        public Guid PlayerGUID { get; set; }
    }
}