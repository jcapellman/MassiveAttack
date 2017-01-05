using System.Collections.Generic;
using System.IO;
using System.Windows;

namespace MassiveAttack.Windows.Editor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        struct LEVELGEOMETRY
        {
            public int TextureID { get; set; }

            public int Scale { get; set; }

            public float X1 { get; set; }

            public float X2 { get; set; }

            public float X3 { get; set; }

            public float X4 { get; set; }

            public float Y1 { get; set; }

            public float Y2 { get; set; }

            public float Y3 { get; set; }

            public float Y4 { get; set; }

            public float Z1 { get; set; }

            public float Z2 { get; set; }

            public float Z3 { get; set; }

            public float Z4 { get; set; }
        }

        public MainWindow()
        {
            InitializeComponent();

            var arrList = new List<LEVELGEOMETRY>();

            var tItem = new LEVELGEOMETRY
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

            tItem = new LEVELGEOMETRY
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

            tItem = new LEVELGEOMETRY
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

            tItem = new LEVELGEOMETRY
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
                using (var bw = new BinaryWriter(fs))
                {
                    bw.Write(arrList.Count);

                    foreach (var item in arrList)
                    {
                        bw.Write(item.TextureID);
                        bw.Write(item.Scale);

                        bw.Write(item.X1);
                        bw.Write(item.Y1);
                        bw.Write(item.Z1);

                        bw.Write(item.X2);
                        bw.Write(item.Y2);
                        bw.Write(item.Z2);

                        bw.Write(item.X3);
                        bw.Write(item.Y3);
                        bw.Write(item.Z3);

                        bw.Write(item.X4);
                        bw.Write(item.Y4);
                        bw.Write(item.Z4);
                    }
                }
            }
        }
    }
}
