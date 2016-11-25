using System;

namespace MassiveAttack.Common.Library.Objects.Common {
    public class ReturnSet<T> {
        public T ObjectValue { get; set; }

        public Exception ExceptionThrown { get; set; }

        public bool HasError => ExceptionThrown != null;

        public ReturnSet() { }

        public ReturnSet(Exception ex) {
            ExceptionThrown = ex;
        } 

        public ReturnSet(T objectValue) {
            ObjectValue = objectValue;
        }
    }
}