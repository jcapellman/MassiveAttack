using System.Collections.Generic;
using System.IO;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using MahApps.Metro.Controls;
using MassiveAttack.Windows.Editor.ViewModels;

namespace MassiveAttack.Windows.Editor
{
    public partial class MainWindow : MetroWindow
    {
        private MainViewModel viewModel => (MainViewModel) DataContext;        

        public MainWindow()
        {
            InitializeComponent();

            DataContext = new MainViewModel();
            MouseLeftButtonDown += MainWindow_MouseDown;
            MouseLeftButtonUp += MainWindow_MouseUp;
            MouseMove += MainWindow_MouseMove;
            MouseRightButtonDown += MainWindow_MouseRightButtonDown;
            /*
            var arrList = new List<MainViewModel.LEVELGEOMETRY>();

            var tItem = new MainViewModel.LEVELGEOMETRY
            {
                TextureID = 1,
                Scale = 20,
                X1 = 100,
                Y1 = -1,
                Z1 = 100,
                X2 = 100,
                Y2 = -1,
                Z2 = 0,
                X3 = 0,
                Y3 = -1,
                Z3 = 0,
                X4 = 0,
                Y4 = -1,
                Z4 = 100
            };

            arrList.Add(tItem);

            tItem = new MainViewModel.LEVELGEOMETRY
            {
                TextureID = 2,
                Scale = 5,
                X1 = 100,
                Y1 = 5,
                Z1 = 100,
                X2 = 100,
                Y2 = 5,
                Z2 = 0,
                X3 = 0,
                Y3 = 5,
                Z3 = 0,
                X4 = 0,
                Y4 = 5,
                Z4 = 100
            };

            arrList.Add(tItem);

            tItem = new MainViewModel.LEVELGEOMETRY
            {
                TextureID = 3,
                Scale = 5,
                X1 = 100,
                Y1 = 5,
                Z1 = 100,
                X2 = 100,
                Y2 = -1,
                Z2 = 100,
                X3 = 0,
                Y3 = -1,
                Z3 = 100,
                X4 = 0,
                Y4 = 5,
                Z4 = 100
            };

            arrList.Add(tItem);

            tItem = new MainViewModel.LEVELGEOMETRY
            {
                TextureID = 4,
                Scale = 5,
                X1 = 100,
                Y1 = 5,
                Z1 = 0,
                X2 = 100,
                Y2 = -1,
                Z2 = 0,
                X3 = 0,
                Y3 = -1,
                Z3 = 0,
                X4 = 0,
                Y4 = 5,
                Z4 = 0
            };

            arrList.Add(tItem);

            using (var fs = File.Open("E1M1.map", FileMode.Create))
            {
                using (var sw = new StreamWriter(fs))
                {
                    sw.WriteLine(arrList.Count);

                    foreach (var item in arrList)
                    {
                        sw.WriteLine($"{item.TextureID} {item.Scale} {item.X1} {item.Y1} {item.Z1} {item.X2} {item.Y2} {item.Z2} {item.X3} {item.Y3} {item.Z3} {item.X4} {item.Y4} {item.Z4}");
                    }
                }
            }

            Application.Current.Shutdown();*/
        }

        private bool _clickUp = false;

        private void MainWindow_MouseRightButtonDown(object sender, MouseButtonEventArgs e)
        {
            _clickUp = true;
        }

        private void MainWindow_MouseMove(object sender, MouseEventArgs e)
        {
            if (_clickUp)
            {
                return;
            }

            line.X2 = e.GetPosition(cMain).X;
            line.Y2 = e.GetPosition(cMain).Y;
        }

        private void MainWindow_MouseUp(object sender, MouseButtonEventArgs e)
        {
            if (_clickUp)
            {
                return;
            }

            cMain.Children.Add(line);
        }

        private void MainWindow_MouseDown(object sender, MouseButtonEventArgs e)
        {
            _clickUp = false;

            startPosition = e.GetPosition(cMain);
            line = new Line();
            line.StrokeThickness = 1;
            line.Stroke = System.Windows.Media.Brushes.Black;
            line.X1 = startPosition.X;
            line.Y1 = startPosition.Y;
        }

        private Point startPosition = default(Point);
        private Line line = new Line();

    }
}
