void pMenu::append(Action &action) {
  if(dynamic_cast<Menu*>(&action)) {
    qtMenu->addMenu(((Menu&)action).p.qtMenu);
  } else if(dynamic_cast<Separator*>(&action)) {
    qtMenu->addAction(((Separator&)action).p.qtAction);
  } else if(dynamic_cast<Item*>(&action)) {
    qtMenu->addAction(((Item&)action).p.qtAction);
  } else if(dynamic_cast<CheckItem*>(&action)) {
    qtMenu->addAction(((CheckItem&)action).p.qtAction);
  } else if(dynamic_cast<RadioItem*>(&action)) {
    qtMenu->addAction(((RadioItem&)action).p.qtAction);
  }
}

void pMenu::remove(Action &action) {
  if(dynamic_cast<Menu*>(&action)) {
    //QMenu::removeMenu() does not exist
    qtMenu->clear();
    for(auto &action : menu.state.action) append(action);
  } else if(dynamic_cast<Separator*>(&action)) {
    qtMenu->removeAction(((Separator&)action).p.qtAction);
  } else if(dynamic_cast<Item*>(&action)) {
    qtMenu->removeAction(((Item&)action).p.qtAction);
  } else if(dynamic_cast<CheckItem*>(&action)) {
    qtMenu->removeAction(((CheckItem&)action).p.qtAction);
  } else if(dynamic_cast<RadioItem*>(&action)) {
    qtMenu->removeAction(((CheckItem&)action).p.qtAction);
  }
}

void pMenu::setFont(const string &font) {
  qtMenu->setFont(pFont::create(font));
  for(auto &item : menu.state.action) item.p.setFont(font);
}

void pMenu::setImage(const image &image) {
  nall::image qtBuffer = image;
  qtBuffer.transform(0, 32u, 255u << 24, 255u << 16, 255u << 8, 255u << 0);

  QImage qtImage(qtBuffer.data, qtBuffer.width, qtBuffer.height, QImage::Format_ARGB32);
  QIcon qtIcon(QPixmap::fromImage(qtImage));
  qtMenu->setIcon(qtIcon);
}

void pMenu::setText(const string &text) {
  qtMenu->setTitle(QString::fromUtf8(text));
}

void pMenu::constructor() {
  qtMenu = new QMenu;
}

void pMenu::destructor() {
  if(action.state.menu) action.state.menu->remove(menu);
  delete qtMenu;
}
