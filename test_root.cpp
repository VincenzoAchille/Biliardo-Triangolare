#include <TCanvas.h>
#include <TH1F.h>

void test_root() {
    // Crea un nuovo istogramma
    TH1F *hist = new TH1F("hist", "Test Istogramma", 100, -5, 5);
    // Riempi l'istogramma con alcuni dati
    hist->FillRandom("gaus", 10000);
    // Crea un canvas e disegna
    TCanvas *c1 = new TCanvas("c1", "Test Canvas", 800, 600);
    hist->Draw();
    c1->SaveAs("test.png");
}

int main() {
    test_root();
    return 0;
}