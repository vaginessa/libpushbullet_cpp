#include "PushBullet.hpp"

#define APIKEY "YpiQLDdMfEkhAFabFZbNwAq8FVcBVGWn"
#define EXAMPLE "{'type': 'note', 'title': 'Note Title', 'body': 'Note Body'}"

using namespace std;

int main(void)
{
    PushBullet pb = PushBullet(APIKEY);
    char* example = "{'type': 'note', 'title': 'Note Title', 'body': 'Note Body'}";

    pb.display();
    cout << pb.getToken() << endl;

    pb.pushing(example);

    return 0;
}