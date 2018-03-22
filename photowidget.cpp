#include "photowidget.h"
#include "ui_photowidget.h"

PhotoWidget::PhotoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhotoWidget)                     // Constructor
{
    ui->setupUi(this);
    QImage image;
    image.load(":/image/th.jpg");
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(image));
    this->setPalette(palette);
    i = 0;
    j = 0;
    label = new QLabel(this);
    ui->scrollArea->setWidget(label);;
    ui->scrollArea->setAlignment(Qt::AlignCenter);
    ui->labelFan->setText(tr("0 / 0"));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(displayImage()));
}

PhotoWidget::~PhotoWidget()                     // Deconstructor
{
    delete ui;
}

void PhotoWidget::on_Openbtn_clicked()          // Open the location of the photos, read all photos
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (dir.isEmpty())
        return;
    imageDir.setPath(dir);;
    QStringList filter;
    filter << "*.jpg" << "*.bmp" << "*.jepg" << "*.png" << "*.xpm";
    imageList = imageDir.entryList(filter, QDir::Files);    // Save the photos which are in the imageDir
    j = imageList.size();
    image_sum = QString::number(j);
    image_position = QString::number(0);
    ui->labelFan->setText(tr("%1 / %2").arg(image_sum).arg(image_position));
}

void PhotoWidget::on_Prevbtn_clicked()          // Show the previous photo
{
    timer->stop();
    --i;
    if (i < 0)
        i = j - 1;
    pix.load(imageDir.absolutePath() + QDir::separator() + imageList.at(i));
    w = label->width();
    h = label->height();
    pix = pix.scaled(w, h, Qt::IgnoreAspectRatio);
    label->setPixmap(pix);
    image_position = QString::number(i + 1);
    ui->labelFan->setText(tr("%1 / %2").arg(image_sum).arg(image_position));
}

void PhotoWidget::on_Playbtn_clicked()          // Start the timer. Play all photos when the timer is timeout
{
    timer->start(1000);
}

void PhotoWidget::on_Stopbtn_clicked()          // Stop the timer
{
    timer->stop();
}

void PhotoWidget::on_Nextbtn_clicked()          // Show the next photo
{
    timer->stop();
    ++i;
    if (i == j)
        i = 0;
    pix.load(imageDir.absolutePath() + QDir::separator() + imageList.at(i));
    w = label->width();
    h = label->height();
    pix = pix.scaled(w, h, Qt::IgnoreAspectRatio);  // Set the photo size be the same as the label size
    label->setPixmap(pix);
    image_position = QString::number(i + 1);
    ui->labelFan->setText(tr("%1 / %2").arg(image_sum).arg(image_position));
}

void PhotoWidget::on_Enlargebtn_clicked()       // Enlarge the photo
{
    timer->stop();
    pix.load(imageDir.absolutePath() + QDir::separator() + imageList.at(i));
    w *= 1.2;
    h *= 1.2;
    pix = pix.scaled(w, h);
    label->setPixmap(pix);
}

void PhotoWidget::on_Rotateleftbtn_clicked()    // Turn the photo 90 degrees to the left, show it
{
    timer->stop();
    matrix.rotate(90);  // Rotate 90 degree
    pix = pix.transformed(matrix, Qt::FastTransformation);
    pix = pix.scaled(label->width(), label->height(), Qt::IgnoreAspectRatio);  // Set the photo size be the same as the label size
    label->setPixmap(pix);
}

void PhotoWidget::on_Rotaterightbtn_clicked()   // Turn the photo 90 degrees to the right, and show it.
{
    timer->stop();
    matrix.rotate(-90); //Rotate -90 degree
    pix = pix.transformed(matrix, Qt::FastTransformation);
    pix = pix.scaled(label->width(), label->height(), Qt::IgnoreAspectRatio);   // Set the photo size be the same as the label size
    label->setPixmap(pix);
}

void PhotoWidget::on_Smallbtn_clicked()         // Smaller the photo
{
    timer->stop();
    pix.load(imageDir.absolutePath() + QDir::separator() + imageList.at(i));
    w *= 0.8;
    h *= 0.8;
    pix = pix.scaled(w, h);
    label->setPixmap(pix);
}

void PhotoWidget::displayImage()                // Show the photo when the timer is timeout
{
    pix.load(imageDir.absolutePath() + QDir::separator() + imageList.at(i));
    w = label->width();
    h = label->height();
    pix = pix.scaled(w, h, Qt::IgnoreAspectRatio);  // Set the photo size be the same as the label size
    label->setPixmap(pix);
    image_position = QString::number(i + 1);
    ++i;
    ui->labelFan->setText(tr("%1 / %2").arg(image_sum).arg(image_position));
    if (i == j)
        i = 0;
}
