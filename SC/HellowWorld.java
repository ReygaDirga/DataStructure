import java.util.Scanner;
/**
 *
 * @author dwiok
 */
public class HellowWorld {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Masukkan nama anda :");
        String nama = scanner.nextLine();
        
        System.out.print("Masukkan nim anda :");
        int nim = scanner.nextInt();
        
        System.out.println("\nHai " + nama + ", nim lu " + nim);
    }
    
}
