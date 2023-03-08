#include "app.h"

int main() {
    application app = applicationCreate("Marine", 1280, 720);
    applicationRun(&app);
    applicationTerminate(&app);
    return 0;
}
