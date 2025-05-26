//
// Created by kubat on 5/26/2025.
//
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "party.h"
#include "d_hondt_allocator.h"
#include <QInputDialog>
#include <QtCharts>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    runSimulation();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::runSimulation() {
    int partyCount = QInputDialog::getInt(this, "Liczba partii", "Podaj liczbę partii:");
    std::vector<Party> parties;
    int totalVotes = 0;

    for (int i = 0; i < partyCount; ++i) {
        QString name = QInputDialog::getText(this, "Nazwa partii", QString("Nazwa partii %1:").arg(i + 1));
        int votes = QInputDialog::getInt(this, "Liczba głosów", QString("Głosy na %1:").arg(name));
        parties.emplace_back(name, votes);
        totalVotes += votes;
    }

    int mandates = QInputDialog::getInt(this, "Mandaty", "Podaj liczbę mandatów do przydzielenia:");

    DHondtAllocator allocator(parties, totalVotes, mandates);
    allocator.allocate();

    // Bar chart
    QtCharts::QBarSet* set = new QtCharts::QBarSet("Mandaty");
    QStringList categories;

    for (const auto& p : parties) {
        *set << p.getMandates();
        categories << p.getName();
    }

    auto series = new QtCharts::QBarSeries();
    series->append(set);

    auto chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Wynik podziału mandatów");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    auto axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto axisY = new QtCharts::QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);
}
