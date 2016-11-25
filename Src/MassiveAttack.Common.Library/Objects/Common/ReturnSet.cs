namespace MassiveAttack.Common.Library.Objects.Common {
    public class ReturnSet<T> {
        public T ObjectValue { get; set; }

        public string ErrorMessage { get; set; }

        public ReturnSet() { } 

        public ReturnSet(T objectValue) {
            ObjectValue = objectValue;
        }
    }
}