using System;
using System.Globalization;
using System.Windows.Data;
using System.Windows.Media;

namespace MassiveAttack.Windows.Frontend.Converters
{
    public class NetworkStatusConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var isConnected = System.Convert.ToBoolean(value.ToString());

            if (isConnected)
            {
                return new SolidColorBrush(Color.FromRgb(0, 0, 255));
            }

            return new SolidColorBrush(Color.FromRgb(255, 0, 0));
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
