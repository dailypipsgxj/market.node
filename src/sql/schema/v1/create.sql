create table users (
    id uuid primary key,
    email varchar(255) not null
);

create table instruments ( 
    id varchar(64) not null primary key, 
    description varchar(255)
);

create table orders ( 
    id uuid primary key,
    timestamp not null integer, 
    buyer_id uuid references users(uuid), 
    seller_id uuid references users(uuid),
    instrument_id not null references instruments(id)
);
