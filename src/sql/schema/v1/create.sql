creaate table users (
    id uuid primary key,
    email varchar(255) not null
) engine=InnoDB;

create table currencies ( 
    symbol varchar(3) not null primary key,
    name varchar(255) not null   
) engine=InnoDB;

create table currency_pairs ( 
    
);

create table orders ( 
    id uuid primary key,
    owner_id uuid references users(id), 
    created_at not null integer,
    is_limit boolean not null,
    is_buy boolean not null,
    price integer,
    quantity integer,
    open_quantity integer,
    state enum('new', 'accepted', 'complete', 'cancelled', 'rejected') not null
) engine=InnoDB;

create table order_executions(
    id uuid primary key,
    timestamp not null integer,
) engine=InnoDB;
