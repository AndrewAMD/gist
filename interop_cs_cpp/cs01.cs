using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace cs01
{
    class cs01
    {
        [DllImport("lib01.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void HelloWorld();

        [DllImport("lib01.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int AddInt(int a, int b);




        static void Main(string[] args)
        {
            HelloWorld();
            int a = 3, b = 4;
            int c = AddInt(a, b);
            string str = "a: " + a + ", b: " + b + ", c: " + c;
            //int* a;


            Console.WriteLine(str);
            
        }
    }
}
