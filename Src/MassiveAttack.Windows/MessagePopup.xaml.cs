using System.ComponentModel;
using System.Runtime.CompilerServices;

using MassiveAttack.Windows.Annotations;

namespace MassiveAttack.Windows
{
    public partial class MessagePopup : INotifyPropertyChanged
    {
        public MessagePopup()
        {
            InitializeComponent();

            DataContext = this;
        }

        private string _content;

        public string MessageContent
        {
            get { return _content; }
            set { _content = value; OnPropertyChanged(); }
        }

        public void ShowMessagePopup(string content)
        {
            MessageContent = content;

            Show();
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
