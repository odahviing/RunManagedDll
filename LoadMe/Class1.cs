using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace LoadMe
{
    public class Class1
    {
        private static readonly DateTime Now = DateTime.Now;

        public static void HelloWorld1()
        {
            MessageBox.Show("Hello World 1 At ." + Now);
            //throw new Exception("ouch");
        }
    }

    public class Class2
    {
        private static readonly DateTime Now = DateTime.Now;

        public static void HelloWorld2()
        {
            MessageBox.Show("Hello World 2 At ." + Now);
            //throw new Exception("ouch");
        }
    }
}