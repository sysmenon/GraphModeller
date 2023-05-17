


//#include <vector>
#include <wx/wxchar.h>
#include <wx/wxprec.h>
#include <wx/grid.h>
#include <stdlib.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/event.h>


class Point {
public:
    Point(wxInt32 xc, wxInt32 yc);
    Point();
    wxInt32 getxcoord();
    wxInt32 getycoord();
    wxString Identity;
    wxString Name;
    wxInt32 x = 0;
    wxInt32 y = 0;
};





class Line {
public:
    Line(Point p, Point q);
    Point p;
    Point q;
};


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    wxVector<Point*> vec;
    wxVector<Line*> lines;
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnPointCreate(wxCommandEvent& event);
    void OnLineCreate(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& evt);

    wxGrid* map = new wxGrid(this, wxID_ANY);
    wxMenu* menuFile = new wxMenu;

    wxInt32 lastXOne;
    wxInt32 lastYOne;
    wxInt32 lastXTwo;
    wxInt32 lastYTwo;
    
    wxDECLARE_EVENT_TABLE();
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

enum
{
    ID_Hello = 1,
    ID_Graph = 2,
    ID_PointCreate = 3,
    ID_LineCreate = 4
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)


EVT_MENU(ID_Hello, MyFrame::OnHello)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_MENU(ID_PointCreate, MyFrame::OnPointCreate)
EVT_MENU(ID_LineCreate, MyFrame::OnLineCreate)


wxEND_EVENT_TABLE()




MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    this->Connect(wxEVT_PAINT, wxPaintEventHandler(MyFrame::OnPaint));
    this->Centre();
    Point* point = new Point(3, 3);

    map->CreateGrid(49, 100);

    for (int i = 0; i < 49; i++) {
        map->DisableRowResize(i);
        for (int j = 0; j < 100; j++) {
            map->DisableColResize(j);
        }
    }
    map->HideColLabels();
    map->HideRowLabels();
    map->SetDefaultColSize(15);
    map->SetDefaultRowSize(1);

    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_LineCreate, "Create a Line");
    menuFile->Append(ID_PointCreate, "Create a Point");
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");

    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");


}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    
}
void MyFrame::OnHello(wxCommandEvent& event)
{

}

void MyFrame::OnPointCreate(wxCommandEvent& event) {

    wxInt32 gridcursorcol = map->GetGridCursorCol();
    wxInt32 gridcursorrow = map->GetGridCursorRow();
    

        //wxLogMessage("Selected point " + wxString::Format(wxT("%i"), gridcursorcol+1) + " " + wxString::Format(wxT("%i"), gridcursorrow+1));
    map->SetCellBackgroundColour(gridcursorrow, gridcursorcol, wxColour("red"));
        

    wxString sNewValue = wxGetTextFromUser(wxT("Enter Name For Point"), wxT("title"), wxT("0"));
    Point* point = new Point(gridcursorcol, gridcursorrow);
   
    map->SetCellValue(gridcursorrow, gridcursorcol, sNewValue);
    point->Name = sNewValue;
    point->Identity = wxString::Format(wxT("%i"), vec.size());
    wxLogMessage(point->Identity + " " + point->Name);
    vec.push_back(point);
     
    //Line* newLine = new Line
}

Point::Point(wxInt32 xc, wxInt32 yc) {
    this->x = xc;
    this->y = yc;
}
wxInt32 Point::getxcoord() {
    return this->x;
}
wxInt32 Point::getycoord() {
    return this->y;
}

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("Hi", wxPoint(50, 50), wxSize(450, 340));

    frame->Show(true);
    return true;
}

void MyFrame::OnPaint(wxPaintEvent &evt) {
    wxGridCellCoords* coords = new wxGridCellCoords(lastXOne, lastYOne);
    wxGridCellCoords* coordstwo = new wxGridCellCoords(lastXTwo, lastYTwo);
    wxRect rect = map->BlockToDeviceRect(*coords, *coordstwo);
    wxPoint p = rect.GetTopLeft();
    wxLogMessage(wxString::Format(wxT("%i"), p.x));
    wxLogMessage(wxString::Format(wxT("%i"), p.y));
    wxPoint q = rect.GetBottomRight();
    wxLogMessage(wxString::Format(wxT("%i"), q.x));
    wxLogMessage(wxString::Format(wxT("%i"), q.y));

    
    wxPaintDC* dc = new wxPaintDC(this);
    wxPen pen;
    pen.SetColour(0, 0, 0);
    pen.SetWidth(100);
    dc->SetPen(pen);
    if (lastXOne != 0) {
        dc->DrawLine(p.x, p.y, q.x, q.y);
    }
   
    evt.Skip();
    
}

void MyFrame::OnLineCreate(wxCommandEvent& evt) {

    wxString sNewValue = wxGetTextFromUser(wxT("Point 1 Name"), wxT("title"), wxT("0"));
    wxString sNewValue2 = wxGetTextFromUser(wxT("Point 2 Name"), wxT("title"), wxT("0"));
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i]->Name == sNewValue) {
            for (int j = 0; j < vec.size(); j++) {
                if (vec[j]->Name == sNewValue2) {
                    Point point(vec[i]->getxcoord(), vec[i]->getycoord());
                    Point point2(vec[j]->getxcoord(), vec[j]->getycoord());
                    //wxLogMessage(wxString::Format(wxT("%i"), vec[i]->getxcoord() + vec[i]->getycoord() + vec[j]->getxcoord() + vec[j]->getycoord()));

                    Line* line = new Line(point, point2);
                    lines.push_back(line);
                    lastXOne = vec[i]->getxcoord();
                    lastYOne = vec[i]->getycoord();
                    lastXTwo = vec[j]->getxcoord();
                    lastYTwo = vec[j]->getycoord();

                }
            }
        }
    }
    wxWindow::Refresh();
    wxWindow::Update();
    
}

Line::Line(Point p, Point q): p(p), q(q) {

}

Point::Point() {

}
