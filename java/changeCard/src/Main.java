import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

//零钱通系统面向过程版
public class Main {
    public static void main(String[] args) {
        double revenue = 0;
        double wallet = 0;
        Date date = null;
        SimpleDateFormat sdp = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        String detil = "---------零钱通明细-----------";
        while (true) {
            //菜单
            System.out.println("---------零钱通菜单-----------");
            System.out.println("1.零钱通明细");
            System.out.println("2.收益入账");
            System.out.println("3·消费");
            System.out.println("4·退出");
            System.out.print("请选择1-4：");
            Scanner s = new Scanner(System.in);
            int shu = s.nextInt();
            if (shu == 1) {
                System.out.println(detil + "\n");
            } else if (shu == 2) {
                System.out.print("输入收益金额：");
                double shusr = s.nextDouble();
                revenue = shusr;
                date = new Date();
                wallet += revenue;
                detil += "\n" + "收益入账\t+" + revenue + "\t" + sdp.format(date) + "\t" + "余额：" + wallet;
            } else if (shu == 3) {
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
            } else if (shu == 4) {
                return;
            } else {
                System.out.println("输错了");
            }
        }


    }
}