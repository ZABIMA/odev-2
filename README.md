Nasıl derlenir ve çalıştırılır (Linux / macOS / Windows WSL):
  gcc -o sharpe_calculator sharpe_calculator.c
  ./sharpe_calculator

Örnek giriş ve çıktı (kullanıcının vereceği sayılar):
  Yatırım getiri oranı (%): 15
  Risksiz faiz oranı (%): 5
  Portföy standart sapması (%): 12

  Hesaplanan Sharpe oranı: 0.8333
  Sınıflandırma: Pozitif ama zayıf (< 1.0)
