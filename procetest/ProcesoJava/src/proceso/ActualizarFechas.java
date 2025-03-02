package proceso;

import java.io.*;
import java.time.LocalDate;

public class ActualizarFechas {
    public static void main(String[] args) {
    	String inputFile = "C:/Users/DELL/Desktop/Procesos/ProcesoJava/bin/proceso/lotes_placeholder.txt";
        String outputFile = "bin/proceso/lotes_actualizados.txt";

        try (BufferedReader br = new BufferedReader(new FileReader(inputFile));
             BufferedWriter bw = new BufferedWriter(new FileWriter(outputFile))) {

            String linea;
            LocalDate today = LocalDate.now();

            while ((linea = br.readLine()) != null) {
                String[] parts = linea.split(",");
                String nombre = parts[0];
                String tipo = parts[1];
                String cantidad = parts[2];
                String idMedicina = parts[3];
                String duracion = parts[4];

                int dia = today.getDayOfMonth();
                int mes = today.getMonthValue();
                int ano = today.getYear();

                bw.write(String.join(",", nombre, tipo, cantidad, idMedicina, duracion, String.valueOf(dia), String.valueOf(mes), String.valueOf(ano)));
                bw.newLine();
            }

        } catch (IOException e) {
            System.err.println("Error al procesar los archivos: " + e.getMessage());
        }
    }
}