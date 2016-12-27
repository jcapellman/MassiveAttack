using System;
using System.Windows;

namespace MassiveAttack.Windows.Frontend
{
    public class BaseWindow : Window
    {
        private MessagePopup _messagePopup;

        protected void ShowMessagePopup(string content)
        {
            if (_messagePopup == null)
            {
                _messagePopup = new MessagePopup();
            }

            _messagePopup.ShowMessagePopup(content);
        }

        protected void ShowMessagePopup(Exception ex)
        {
            ShowMessagePopup(ex.ToString());
        }
    }
}