using System.Collections.Generic;
using System.Collections.ObjectModel;
using MassiveAttack.Common.Library.Objects.WebAPI.Settings;
using Vulkan;

namespace MassiveAttack.Windows.ViewModels
{
    public class SettingsViewModel : BaseViewModel
    {
        private SettingsResponseItem _settings;

        public SettingsResponseItem Settings
        {
            get { return _settings; }
            set { _settings = value; OnPropertyChanged(); }
        }

        private ObservableCollection<PhysicalDeviceProperties> _devices;

        public ObservableCollection<PhysicalDeviceProperties> Devices
        {
            get { return _devices; }
            set { _devices = value; OnPropertyChanged(); }
        }

        public SettingsViewModel()
        {
            Settings = new SettingsResponseItem
            {
                BPP = 16,
                ResolutionX = 1024,
                ResolutionY = 768
            };            
        }

        public void InitializeSettings()
        {
            Devices = new ObservableCollection<PhysicalDeviceProperties>();

            var devices = new ObservableCollection<PhysicalDevice>(App.instance.EnumeratePhysicalDevices());

            foreach (var device in devices)
            {
                var props = device.GetProperties();

                Devices.Add(props);
            }            
        }
    }
}