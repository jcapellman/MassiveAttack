using System.ComponentModel;
using System.Runtime.CompilerServices;

using MassiveAttack.Common.Library.Enums;
using MassiveAttack.Common.Library.Objects.Common;

namespace MassiveAttack.Windows.ViewModels {
    public class BaseViewModel : INotifyPropertyChanged
    {
        private string _token;
        private string _webapiService;

        public HandlerConstructorItem handlerWrapper => new HandlerConstructorItem
        {
            Token = _token,
            WebAPIService = _webapiService,
            CurrentPlatfrom = PLATFORMS.WINDOWS
        };

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}