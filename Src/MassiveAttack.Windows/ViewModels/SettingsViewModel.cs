using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using MassiveAttack.Common.Library.Enums;
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

        private PhysicalDeviceProperties _selectedDevice;

        public PhysicalDeviceProperties SelectedDevice
        {
            get { return _selectedDevice; }
            set { _selectedDevice = value; OnPropertyChanged(); }
        }

        private List<string> _TextureDetails;

        public List<string> TextureDetails
        {
            get { return _TextureDetails; }
            set { _TextureDetails = value; OnPropertyChanged(); }
        }

        private string _selectedTextureDetail;

        public string SelectedTextureDetail { get { return _selectedTextureDetail; } set { _selectedTextureDetail = value; OnPropertyChanged(); } }

        public SettingsViewModel()
        {
            Settings = new SettingsResponseItem
            {
                BPP = 16,
                ResolutionX = 1024,
                ResolutionY = 768,
                TextureDetail = TEXTURE_DETAIL.INSANE
            };            
        }

        public void InitializeSettings()
        {
            Devices = new ObservableCollection<PhysicalDeviceProperties>();

            var devices = new ObservableCollection<PhysicalDevice>(App.instance.EnumeratePhysicalDevices());

            foreach (var device in devices)
            {
                var props = device.GetProperties();

                if (props.DeviceId == Settings.DeviceID)
                {
                    SelectedDevice = props;
                }

                Devices.Add(props);
            }

            TextureDetails = Enum.GetNames(typeof (TEXTURE_DETAIL)).ToList();

            SelectedTextureDetail = Settings.TextureDetail.ToString();
        }
    }
}