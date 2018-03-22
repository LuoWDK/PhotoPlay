#ifndef PHOTOWIDGET_H
#define PHOTOWIDGET_H

#include <QWidget>
#include <QStringList>
#include <QString>
#include <QTimer>
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QMatrix>
#include <QImage>
#include <QBrush>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class PhotoWidget;
}

class PhotoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PhotoWidget(QWidget *parent = 0);
    ~PhotoWidget();

private slots:
    void on_Openbtn_clicked();          // Open the location of the photos

    void on_Prevbtn_clicked();          // Show the previous photo

    void on_Playbtn_clicked();          // Start the timer. Play next photo when the timer is timeout

    void on_Stopbtn_clicked();          // Stop the timer

    void on_Nextbtn_clicked();          // Show the next photo

    void on_Enlargebtn_clicked();       // Enlarge the photo

    void on_Rotateleftbtn_clicked();    // Turn 90 degrees to the left

    void on_Rotaterightbtn_clicked();   // Turn 90 degrees to the right

    void on_Smallbtn_clicked();         // Smaller the photo

    void displayImage();                // Show the photo

private:
    Ui::PhotoWidget *ui;
    QTimer *timer;                      // A one second (1000 millisecond) timer to play automatically
    QLabel *label;                      // A label to show photo
    QPixmap pix;                        // QPixmap provides several ways of reading an image file
    QMatrix matrix;                     // A matrix is used to rotate photo
    int i, j;
    qreal w, h;                         // Used to zoom in/out photo
    QString image_sum, image_position;  // Number of photos, position of current photo
    QStringList imageList;              // Used to save the photos
    QDir imageDir;                      // The absolute path of the photos
};

#endif // PHOTOWIDGET_H
