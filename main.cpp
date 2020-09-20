// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".

//#include <vector>
#include <wx/wxchar.h>
#include <wx/wxprec.h>
#include <wx/grid.h>
#include <stdlib.h>
#include <cmath>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/event.h>


class Point {
public:
    Point(wxInt32 xc, wxInt32 yc);
    Point(wxInt32 xc, wxInt32 yc, wxString Identity, wxString Name);
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
    bool visited;

};


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    wxVector<Point*> vec;
    wxVector<Line*> lines;
    wxVector<Point> GetPointNeighbour(Point point);
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnPointCreate(wxCommandEvent& event);
    void OnLineCreate(wxCommandEvent& event);
    void BruteForce(wxCommandEvent& event);
    wxInt32 distance(Point p, Point q);
    void lookAt(Point point, wxString endpoint);
    Line* find(Point p, Point q);
    wxVector<Line*> GetLineNeighbour(Point point);
    void SetVisitedFalse(wxVector<Line*> vec);
    void SetVisitedTrue(wxVector<Line*> vec);

    wxGrid* map = new wxGrid(this, wxID_ANY);
    wxMenu* menuFile = new wxMenu;

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
    ID_LineCreate = 4,
    ID_BruteForce = 5
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)


EVT_MENU(ID_Hello, MyFrame::OnHello)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_MENU(ID_PointCreate, MyFrame::OnPointCreate)
EVT_MENU(ID_LineCreate, MyFrame::OnLineCreate)
EVT_MENU(ID_BruteForce, MyFrame::BruteForce)


wxEND_EVENT_TABLE()




MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{

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
    menuFile->Append(ID_LineCreate, "Create a Line...\tCtrl-G");
    menuFile->Append(ID_PointCreate, "Create a Point...\tCtrl-H");
    menuFile->Append(ID_Hello, "&Hello...");
       
    menuFile->Append(ID_BruteForce, "End Graph and Brute Force Search");

    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&Graph");
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
    wxMessageBox("This is a wxWidgets' Hello world sample",
        "About Hello World", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
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
    MyFrame* frame = new MyFrame("Hello World", wxPoint(50, 50), wxSize(450, 340));

    frame->Show(true);
    return true;
}



void MyFrame::OnLineCreate(wxCommandEvent& evt) {

    wxString sNewValue = wxGetTextFromUser(wxT("Point 1 Name"), wxT("title"), wxT("0"));
    wxString sNewValue2 = wxGetTextFromUser(wxT("Point 2 Name"), wxT("title"), wxT("0"));
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i]->Name == sNewValue) {
            for (int j = 0; j < vec.size(); j++) {
                if (vec[j]->Name == sNewValue2) {
                    Point point(vec[i]->getxcoord(), vec[i]->getycoord(), vec[i]->Name, vec[i]->Identity);
                    Point point2(vec[j]->getxcoord(), vec[j]->getycoord(), vec[j]->Name, vec[j]->Identity);
                    //wxLogMessage(wxString::Format(wxT("%i"), vec[i]->getxcoord() + vec[i]->getycoord() + vec[j]->getxcoord() + vec[j]->getycoord()));

                    Line* line = new Line(point, point2);
                    lines.push_back(line);

                }
            }
        }
    }
   
}

Line::Line(Point p, Point q) : p(p), q(q) {

}

Point::Point(wxInt32 xc, wxInt32 yc, wxString Name, wxString Identity): x(xc), y(yc), Name(Name), Identity(Identity) {

}

wxInt32 MyFrame::distance(Point p, Point q) {
    if (p.x > q.x) {
        if (p.y > q.y) {
            return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
        }
        else {
            return sqrt((p.x - q.x) * (p.x - q.x) + (q.y - p.y) * (q.y - p.y));
        }
    }
    else{
        if (p.y > q.y) {
            return sqrt((q.x - p.x) * (q.x - p.x) + (p.y - q.y) * (p.y - q.y));
        }
        else {
            return sqrt((q.x - p.x) * (q.x - p.x) + (q.y - p.y) * (q.y - p.y));
        }
    }
}

Line* MyFrame::find(Point p, Point q) {
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i]->p.Name == p.Name and lines[i]->q.Name == q.Name) {
            return lines[i];
        }
        else if (lines[i]->p.Name == q.Name and lines[i]->q.Name == p.Name) {
            return lines[i];
        }
    }
  
}

wxVector<Line*> MyFrame::GetLineNeighbour(Point point) {
    wxVector<Line*> linelist;
    for (int i = 0; i < lines.size(); i++) {
        if (point.Name == lines[i]->q.Name) {
            linelist.push_back(lines[i]);
        }
        if (point.Name == lines[i]->p.Name) {
            linelist.push_back(lines[i]);
        }
    }
    return linelist;
}
wxVector<Point> MyFrame::GetPointNeighbour(Point point) {
    wxVector<Point> pointlist;
    
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i]->p.Name == point.Name and lines[i]->q.Name == point.Name) {
            continue;
        }
        if (lines[i]->p.Name == point.Name) {
            pointlist.push_back(lines[i]->q);
        }
        if (lines[i]->q.Name == point.Name) {
            pointlist.push_back(lines[i]->p);
        }
    }
    return pointlist;
}

void MyFrame::SetVisitedFalse(wxVector<Line*> vec) {
    for (int i = 0; i < vec.size(); i++) {
        vec[i]->visited = false;
    }
}

void MyFrame::SetVisitedTrue(wxVector<Line*> vec) {
    for (int i = 0; i < vec.size(); i++) {
        vec[i]->visited = true;
    }
}

void MyFrame::lookAt(Point point, wxString endpoint) {
    wxVector<Point> pointlist = GetPointNeighbour(point);
    wxVector<Line*> linelist = GetLineNeighbour(point);
    wxLogMessage(point.Name);
    for (int i = 0; i < pointlist.size(); i++) {
        if (pointlist[i].Name == endpoint) {
            wxLogMessage("success");
            break;

        }
        else if(pointlist.size() == 1 and GetPointNeighbour(pointlist[i]).size() == 1) {
            wxLogMessage("failure");
 
        }

        if (find(pointlist[i], point)->visited == false) {
            find(pointlist[i], point)->visited = true;
            
            lookAt(pointlist[i], endpoint);

            find(pointlist[i], point)->visited = false;
        }
        else {
            wxLogMessage("failure");
        }
    }
}


void MyFrame::BruteForce(wxCommandEvent& evt) {
    wxString sNewValue = wxGetTextFromUser("Start");
    wxString sNewValue2 = wxGetTextFromUser("End");
    SetVisitedFalse(lines);
    for (int i = 0; i < vec.size(); i++) {
        
        if (vec[i]->Name == sNewValue) {
            lookAt(*vec[i], sNewValue2);
            //bool existentpath = lookAt(*vec[i], sNewValue2);
            //wxLogMessage(wxString::Format(wxT("%i"), existentpath));
        }
    }
    
}

