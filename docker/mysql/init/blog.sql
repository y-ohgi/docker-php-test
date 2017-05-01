CREATE DATABASE blog;
USE blog;

CREATE TABLE Categories(
  id int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  name varchar(30) NOT NULL UNIQUE
);
INSERT INTO Categories(id, name) VALUES
  (1, "ゲーム"),
  (2, "生活"),
  (3, "料理"),
  (4, "プログラミング");

CREATE TABLE PublishStates(
  id int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  state varchar(10) NOT NULL UNIQUE
);
INSERT INTO PublishStates(id, state) VALUES
  (1, "下書き"),
  (2, "非公開"),
  (3, "公開");

CREATE TABLE PendingRegistrations(
  email varchar(255) NOT NULL UNIQUE,
  hash varchar(255) NOT NULL UNIQUE,
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  INDEX(email)
);

CREATE TABLE Users(
  id int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  name varchar(30) NOT NULL UNIQUE,
  email varchar(255) NOT NULL UNIQUE,
  password varchar(255) NOT NULL,
  description varchar(255),
  icon_path varchar(255),
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  updated_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  INDEX(email)
);

CREATE TABLE Blogs(
  id int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  category_id int(11) NOT NULL,
  title varchar(140) NOT NULL,
  description TEXT,
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  updated_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  FOREIGN KEY (`category_id`) REFERENCES `Categories`(`id`)
);

CREATE TABLE BlogUsers(
  user_id int(11) NOT NULL,
  blog_id int(11) NOT NULL,
  INDEX(user_id, blog_id),
  FOREIGN KEY (`user_id`) REFERENCES `Users`(`id`),
  FOREIGN KEY (`blog_id`) REFERENCES `Blogs`(`id`)
);

CREATE TABLE Posts(
  id int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  user_id int(11) NOT NULL,
  blog_id int(11) NOT NULL,
  publish_state_id int(11) NOT NULL DEFAULT 1, # デフォルトは下書き状態にする
  title varchar(140) NOT NULL,
  content TEXT,
  page_view int(11) UNSIGNED NOT NULL DEFAULT 0,
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  updated_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  INDEX(user_id, blog_id),
  FOREIGN KEY (`user_id`) REFERENCES `Users`(`id`),
  FOREIGN KEY (`blog_id`) REFERENCES `Blogs`(`id`)
);

CREATE TABLE Comments(
  id int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  post_id int(11) NOT NULL,
  user_id int(11) NOT NULL,
  content varchar(255) NOT NULL,
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  INDEX(post_id),
  FOREIGN KEY (`post_id`) REFERENCES `Posts`(`id`),
  FOREIGN KEY (`user_id`) REFERENCES `Users`(`id`)
);
