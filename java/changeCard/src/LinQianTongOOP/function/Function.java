package LinQianTongOOP.function;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

public class Function {
    double revenue = 0;
    double wallet = 0;
    Date date = null;
    SimpleDateFormat sdp = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
    String detil = "---------零钱通明细-----------";
    Scanner s = new Scanner(System.in);


    public void menu() {
        boolean flags = true;
        do {
            //选项
            System.out.println("---------零钱通菜单-----------");
            System.out.println("1.零钱通明细");
            System.out.println("2.收益入账");
            System.out.println("3·消费");
            System.out.println("4·退出");
            System.out.print("请选择1-4：");
            int choose = s.nextInt();
            switch (choose) {
                case 1:
                    homePage();
                    break;
                case 2:
                    earnings();
                    break;
                case 3:
                    consume();
                    break;
                case 4:
                    //法1
                    String yn = "";
                    while (true) {
                        System.out.print("确认要退出吗：（y/n）");
//                        Scanner s1 = new Scanner(System.in);
                        yn = s.next();
                        if ("y".equals(yn) || "n".equals(yn)) {
                            //System.out.println("进入yn");
                            break;
                        } else {
                            System.out.println("yn输错了");
                        }
                    }
                    switch (yn) {
                        case "y":
                            flags = false;
                            System.out.println(flags);
                            break;
                        case "n":
                            //flags = false;
                            break;
                    }
                    break;
                //法二
//                    while (true) {
//                        System.out.print("确认要退出吗：（y/n）");
//                        Scanner s1  = new Scanner(System.in);
//                        String yn = s1.next();
//                       // String yn = "n";
//                        if ("y".equle(yn)) {
//                            System.out.println(yn);
//                            flags = false;
//                            break;
//                        } else if ("y".equle(yn)) {
//                            System.out.println(yn);
//                            break;
//                        }
//                        System.out.println("输错了");
//                        //continue;
//                        break;
//                    }
                //  break;
                default:
                    System.out.println("选项输错");
            }
        } while (flags);

    }

    //1
    public void homePage() {
        System.out.println(detil + "\n");
    }

    //2
    public void earnings() {
        System.out.print("输入收益金额：");
        double shusr = s.nextDouble();
        revenue = shusr;
        date = new Date();
        wallet += revenue;
        detil += "\n" + "收益入账\t+" + revenue + "\t" + sdp.format(date) + "\t" + "余额：" + wallet;
    }

    //3
    public void consume() {
        System.out.print("输入消费金额：");
        double shuXF = s.nextDouble();
        revenue = shuXF;
        if(revenue > wallet){
            System.out.println("钱不够");
        }
        else {
            wallet -= revenue;
            date = new Date();
            detil += "\n" + "消费    \t-" + revenue + "\t" + sdp.format(date) + "\t" + "余额：" + wallet;
        }
    }

}
class Main {
    public static void main(String[] args) {
        Function function = new Function();
        function.menu();
    }
}
